import socket

def send_bytes(hostname, port, data):
    # Create a TCP/IP socket
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    try:
        # Connect the socket to the server
        server_address = (hostname, port)
        print(f"Connecting to {server_address}")
        sock.connect(server_address)

        # Send the data
        print(f"Sending data: {data}")
        sock.sendall(data)

        # Receive a response (optional, can be removed if not needed)
        response = sock.recv(1024)
        print(f"Received response: {response}")

    finally:
        # Close the socket
        print("Closing socket")
        sock.close()

if __name__ == "__main__":
    hostname = "127.0.0.1"
    port = 12345
    data = bytes.fromhex("00000002DEADBEEF")
    send_bytes(hostname, port, data)
