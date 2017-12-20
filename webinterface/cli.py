import socket
import sys

server_address = '/tmp/smartcardsrv'

# Create a UDS socket
sock = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)

# Connect the socket to the port where the server is listening
print >>sys.stderr, 'connecting to %s' % server_address
try:
    sock.connect(server_address)
except socket.error, msg:
    print >>sys.stderr, msg
    sys.exit(1)

try:
    # Send data
    # message = 'BTN-IP'
    message = 'fk28391083'
    print >>sys.stderr, 'sending "%s"' % message
    sock.sendall(message)
finally:
    print >>sys.stderr, 'closing socket'
    sock.close()
