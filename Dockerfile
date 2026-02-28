FROM ubuntu:22.04

# Avoid interactive prompts
ENV DEBIAN_FRONTEND=noninteractive

WORKDIR /app

COPY . .

# Install compiler + minimal Boost needed by Crow
RUN apt-get update && \
    apt-get install -y g++ make \
    libboost-system-dev \
    libboost-filesystem-dev \
    libboost-thread-dev && \
    rm -rf /var/lib/apt/lists/*

# Compile all C++ files
RUN g++ -std=c++17 *.cpp -o app -pthread

EXPOSE 8080

CMD ["./app"]
