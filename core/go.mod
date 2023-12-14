module github.com/schollz/-core/core

go 1.21

replace github.com/schollz/-core/core/src/op1 => ./src/op1

replace github.com/schollz/-core/core/src/renoise => ./src/renoise

replace github.com/schollz/-core/core/src/sox => ./src/sox

replace github.com/schollz/-core/core/src/utils => ./src/utils

require (
	github.com/bep/debounce v1.2.1
	github.com/gorilla/websocket v1.5.1
	github.com/lucasepe/codename v0.2.0
	github.com/schollz/logger v1.2.0
	github.com/stretchr/testify v1.8.4
	go.etcd.io/bbolt v1.3.8
)

require (
	github.com/davecgh/go-spew v1.1.1 // indirect
	github.com/pmezard/go-difflib v1.0.0 // indirect
	golang.org/x/net v0.19.0 // indirect
	golang.org/x/sys v0.15.0 // indirect
	gopkg.in/yaml.v3 v3.0.1 // indirect
)