FROM ubuntu:22.04

# Add i386 architecture and lic6 for 32-bit support
# and utilities for debugging
RUN dpkg --add-architecture i386 && \
    apt-get update && \
    apt-get install -y libc6:i386 sudo gcc gcc-multilib gdb python3

# Add user ubuntu with sudo privileges to be helpful
RUN adduser ubuntu --disabled-password --gecos "" && \
    echo "ubuntu ALL=(ALL) NOPASSWD: ALL" >> /etc/sudoers

WORKDIR /home/ubuntu

# Copy the files to the image
COPY rick* .

# Compile the files and set the setuid bit on rick
RUN gcc -m32 -o rick_real rick.c -no-pie && \
    gcc -m32 -o rick rick_wrap.c -no-pie && \
    chown root:root rick_real && \
    chown root:root rick && \
    chmod +s rick

# Run as user ubuntu by default
USER ubuntu
