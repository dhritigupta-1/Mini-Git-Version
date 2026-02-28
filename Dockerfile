FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

WORKDIR /app

COPY . .

# Install compiler + required Boost libraries for Crow
RUN apt-get update && \
    apt-get install -y g++ make \
    libboost-system-dev \
    libboost-filesystem-dev \
    libboost-thread-dev && \
    rm -rf /var/lib/apt/lists/*

# Compile ONLY the Crow server + logic files
RUN g++ -std=c++17 server.cpp Repository.cpp -o app -pthread

EXPOSE 8080

CMD ["./app"]
