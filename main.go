package main

import "fmt"
import "net"
import "github.com/nurfed1/go-socks"

// this project fails for some reason when ran using rundll, however reflective dll shellcode does work.
func main() {
	fmt.Println("Starting server")

	socksConf := &socks.Config{}
	socksServer, err := socks.New(socksConf)
	if err != nil {
		panic(err)
	}

	// l, err := net.Listen("tcp", "0.0.0.0:80")
	l, err := net.Listen("tcp", "0.0.0.0:8080")
	if err != nil {
		panic(err)
	}
	for {
		conn, err := l.Accept()
		if err != nil {
			panic(err)
		}

		// fmt.Println("accepted")
		go socksServer.ServeConn(conn)
	}
}
