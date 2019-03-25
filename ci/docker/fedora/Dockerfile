FROM fedora:latest

RUN dnf -y update \
&& dnf -y groupinstall "Development Tools" \
&& dnf -y install cmake gcc-c++ \
&& dnf clean all
