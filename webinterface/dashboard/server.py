import socket
import time
import sys
import os

server_address = '/tmp/smartcardsrv'
sleep_time = 5

try:
    # Make sure the socket does not already exist
    os.unlink(server_address)
except OSError:
    if os.path.exists(server_address):
        raise

# Create a UDS socket
sock = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
print >>sys.stderr, 'starting up on %s' % server_address
sock.bind(server_address)

# Listen for incoming connections
sock.listen(1)

def manage_input():
    while True:
        # Wait for a connection
        print >>sys.stderr, 'waiting for a connection'
        connection, _ = sock.accept()
        from dashboard.models import Token, RegisteredToken, AccessAttempt
        from dashboard.client import send_message
        
        try:
            print >>sys.stderr, 'connected'
            while True:
                data = connection.recv(30)
                if data:
                    print >>sys.stderr, 'received "%s"' % data
                    if data == 'BTN-IP':
                        send_message('SHOW-IP')
                    else:
                        send_message('CHECK')
                        time.sleep(sleep_time)
                        aa = AccessAttempt()
                        try:
                            tk = Token.objects.get(token=data)
                            aa.token = tk
                            aa.result = tk.enabled
                            if tk.enabled:
                                send_message('ACCEPT')
                            else:
                                send_message('FAIL')
                        except Token.DoesNotExist:
                            utk = Token()
                            utk.token = data
                            utk.save()
                            aa.token = utk
                            aa.result = False
                            send_message('FAIL')
                        aa.save()
                    time.sleep(sleep_time)
                else:
                    break
        except Exception as e:
            print e
        finally:
            print >>sys.stderr, 'connection end'
            # Clean up the connection
            connection.close()
            send_message('IDLE')

