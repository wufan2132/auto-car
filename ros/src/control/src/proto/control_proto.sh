#!/usr/bin/env bash

protoc ./pid_conf.proto --cpp_out=./  
protoc ./lon_controller_conf.proto --cpp_out=./
protoc ./control_conf.proto --cpp_out=./