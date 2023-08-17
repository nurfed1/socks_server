DIR=./bin

LDFLAGS=-ldflags "-s -w"
GCFLAGS=-gcflags=all="-N -l"

GOFILES=`go list ./...`
GOFILESNOTEST=`go list ./... | grep -v test`

# Make Directory to store executables
$(shell mkdir -p ${DIR})

linux: lint
	env CGO_ENABLED=0 GOOS=linux GOARCH=amd64 go build -trimpath ${LDFLAGS} -o ${DIR}/socks_server .

debug: lint
	env CGO_ENABLED=0 GOOS=linux GOARCH=amd64 go build -trimpath ${GCFLAGS} -o ${DIR}/socks_server .

windows: lint
	env CGO_ENABLED=1 GOOS=windows GOARCH=amd64 go build -trimpath ${LDFLAGS} -o ${DIR}/socks_server.exe .

windows_hide: lint
	env CGO_ENABLED=1 GOOS=windows GOARCH=amd64 go build -trimpath -ldflags "-s -w -H=windowsgui" -o ${DIR}/socks_server.exe .

windows_dll: lint
	env CGO_ENABLED=1 CC="x86_64-w64-mingw32-gcc" GOOS=windows go build -tags dll -trimpath -ldflags "-s -w -H windowsgui" -buildmode=c-shared -o ${DIR}/socks_server.dll .

# reflective dll
shellcode: windows_dll
	./srdi/srdi bin/socks_server.dll Start

all: linux windows windows_hide windows_dll shellcode

dep: ## Get the dependencies
	@go get -v -d ./...
	@go get -u all
	@go mod tidy

lint: ## Lint the files
	@go fmt ${GOFILES}
# @go vet ${GOFILESNOTEST}

clean:
	@rm -rf ${DIR}/*

.PHONY: all linux windows windows_hide windows_dll shellcode dep lint clean
