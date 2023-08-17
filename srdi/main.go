package main

import (
    "fmt"
    "os"
    // "github.com/bishopfox/sliver/server/generate"
)

func main() {
    if len(os.Args) < 2 {
        fmt.Printf("Usage: %s <file.dll> <startFunction>", os.Args[0])
        os.Exit(1)
    }

    dllPath := os.Args[1]
    startFunction := os.Args[2]

    if _, err := os.Stat(dllPath); err != nil {
        fmt.Println("File does not exist")
        os.Exit(1)
    }

    shellcodePath, err := ShellcodeRDIToFile(dllPath, startFunction)

    if err != nil {
        panic(err)
    }

    fmt.Printf("Output file: %s.\n", shellcodePath)
}
