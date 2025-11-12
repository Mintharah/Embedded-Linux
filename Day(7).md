# Client
````bash
  import socket

HOST = "127.0.0.1"
PORT = 5000

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect((HOST, PORT))

num1 = input("Enter first number: ")
num2 = input("Enter second number: ")
op = input("Enter operation (+, -, *, /): ")

message = f"{num1} {num2} {op}"
client_socket.send(message.encode())

result = client_socket.recv(1024).decode()
print(f"[CLIENT] Result: {result}")

client_socket.close()

````

# Server
```bash
  import socket

HOST = "127.0.0.1"
PORT = 5000

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind((HOST, PORT))
server_socket.listen(1)

print("[SERVER] Waiting for connection...")
conn, addr = server_socket.accept()
print(f"[SERVER] Connected by {addr}")

data = conn.recv(1024).decode()
num1, num2, op = data.split()
num1, num2 = float(num1), float(num2)

if op == '+':
    result = num1 + num2
elif op == '-':
    result = num1 - num2
elif op == '*':
    result = num1 * num2
elif op == '/':
    result = num1 / num2 if num2 != 0 else "Error: divide by zero"
else:
    result = "Error: unknown operation"

conn.send(str(result).encode())
conn.close()
server_socket.close()
print("[SERVER] Done.")

```
