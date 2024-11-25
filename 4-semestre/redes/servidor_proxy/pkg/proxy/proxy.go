package proxy

import (
	"fmt"
	"math"
	"net"
	"strings"
)

func convert_request_line(request_line string) (method, target, path, version string) {
	request_line = strings.TrimSpace(request_line)
	parts := strings.Split(request_line, " ")
	if len(parts) != 3 {
		return
	}

	method = parts[0]
	version = parts[2]

	target = ""
	slash_count := 0
	i := 0
	for slash_count < 3 {
		if len(parts[1]) == 0 {
			break
		}
		if parts[1][i] == '/' {
			slash_count++
		}
		if slash_count < 3 {
			target += string(parts[1][i])
			i++
		}
	}
	path = parts[1][i:]
	return
}

type Proxy struct {
	listen_socket net.Listener
}

func NewProxy(port int) *Proxy {
	var err error
	p := &Proxy{}
	p.listen_socket, err = net.Listen("tcp", fmt.Sprintf(":%d", port))
	if err != nil {
		panic(err)
	}
	return p
}

func (p *Proxy) handleConnection(conn net.Conn) {
	defer conn.Close()
	buff := make([]byte, int(math.Pow(2, 16)))
	for {
		n, err := conn.Read(buff)
		if err != nil || n == 0 {
			break
		}

		request_line_end := strings.Index(string(buff), "\r\n")
		if request_line_end == -1 {
			break
		}
		request_line := string(buff[:request_line_end])
		method, target, path, version := convert_request_line(request_line)

		// Connect to the target server
		domain := strings.Split(target, "://")[1]
		target_conn, err := net.Dial("tcp", domain+":80")
		if err != nil {
			fmt.Println(err)
			break
		}
		defer target_conn.Close()

		new_request_line := fmt.Sprintf("%s %s %s", method, path, version)
		new_request := strings.Replace(string(buff), request_line, new_request_line, 1)
		fmt.Println(new_request)

		target_conn.Write([]byte(new_request))
		target_conn.Read(buff)
		conn.Write(buff)
	}
}

func (p *Proxy) Run() {
	for {
		conn, err := p.listen_socket.Accept()
		if err != nil {
			panic(err)
		}
		go p.handleConnection(conn)
	}
}
