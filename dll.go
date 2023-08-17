//go:build dll

package main

import (
	"C"
	"unsafe"
)

//export OnProcessAttach
func OnProcessAttach(
	hinstDLL unsafe.Pointer, // handle to DLL module
	fdwReason uint32, // reason for calling function
	lpReserved unsafe.Pointer, // reserved
) {
	main()
}

//export Start
func Start() {
	main()
}
