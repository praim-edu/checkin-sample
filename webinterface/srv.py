import socket
import sys
import os

server_address = '/tmp/socket'

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

while True:
    # Wait for a connection
    print >>sys.stderr, 'waiting for a connection'
    connection, _ = sock.accept()
    try:
        print >>sys.stderr, 'connected'
        while True:
            data = connection.recv(16)
            if data:
                print >>sys.stderr, 'received "%s"' % data                
            else:
                break

    finally:
        print >>sys.stderr, 'connection end'
        # Clean up the connection
        connection.close()
