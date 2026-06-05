# Simple-HTTP-Server
_A lightweight HTTP server that handles TCP connections and serves text files. The requested file path is provided via an HTTP GET request. If the file exists, the server returns a 200 OK response with its content; otherwise, it responds with 404 Page Not Found._

## Features
- Handles TCP connections on a predefined port (default: 80)
- Parses HTTP GET requests from clients
- Serves text files from a predefined directory
- Returns proper HTTP responses:
  - 200 OK – when the file exists
  - 404 Page Not Found – when the file does not exist
- Simple and lightweight implementation

## Example HTTP GET Request
```
GET /example.txt HTTP/1.1
Host: localhost
User-Agent: Chrome/100.0
Accept: text/html
Connection: keep-alive
```
### Explanation:
GET          → request method<br>
/example.txt → file path<br>
HTTP/1.1     → protocol version<br>
Host         → server address<br>
User-Agent   → client identity<br>
Accept       → expected content<br>
Connection   → connection type<br>

_To "make"       run in terminal:  "make server"_
_To "make clean" run in terminal:  "make server_clean"_
