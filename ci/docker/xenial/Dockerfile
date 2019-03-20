FROM ubuntu:xenial
LABEL maintainer="corentinl@google.com"

RUN apt-get update -q && \
apt-get install -yq git wget build-essential cmake && \
apt-get clean && \
rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*
