# Simple-HTTP-Server-RPI2-
_A lightweight HTTP server implemented for Raspberry Pi 2 that handles TCP connections and serves text files from a predefined directory. The requested file path is provided via an HTTP GET request. If the file exists, the server returns a 200 OK response with its content; otherwise, it responds with 404 Page Not Found._

## Features
- Handles TCP connections on a predefined port (default: 80)
- Parses HTTP GET requests from clients
- Serves text files from a predefined directory
- Returns proper HTTP responses:
  - 200 OK – when the file exists
  - 404 Page Not Found – when the file does not exist
- Simple and lightweight implementation

## Theoretical Background
### TCP (Transmission Control Protocol) is the foundation on which HTTP operates.
It is a reliable protocol that:
- Guarantees data delivery
- Preserves the order of packets
- Detects errors and retransmits lost data
### HTTP Protocol
- HTTP (HyperText Transfer Protocol) is the communication language between clients (browsers, apps) and web servers.
- It works over TCP/IP, ensuring reliable communication.
### HTTP Methods
Common HTTP methods include:
  GET – requests data from the server
  POST – sends data to the server
  PUT / DELETE – modify or remove resources
_This project focuses on the GET method, which retrieves files without modifying server state._

## Example HTTP GET Request
```
GET /example.txt HTTP/1.1
Host: localhost
User-Agent: Chrome/100.0
Accept: text/html
Connection: keep-alive
```
### Explanation:
GET          → request method
/example.txt → file path
HTTP/1.1     → protocol version
Host         → server address
User-Agent   → client identity
Accept       → expected content
Connection   → connection type

# How it works:
1. Start the server:
```sudo./server```
2. Send request from browser/Postman:
```http://localhost/example.txt```
3. Server workflow:
Parses request → ParseRequest
Checks file existence
Sends response:
  200 OK + file content (SendResponse)
  404 Page Not Found (SendError)
