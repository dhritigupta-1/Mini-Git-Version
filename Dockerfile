FROM gcc:11

WORKDIR /app

COPY . .

# Install Boost (required by Crow)
RUN apt-get update && apt-get install -y libboost-all-dev

# Compile ALL source files for Linux
RUN g++ -std=c++17 *.cpp -o app -pthread

EXPOSE 8080

CMD ["./app"]
