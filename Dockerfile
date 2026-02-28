FROM gcc:11

WORKDIR /app

COPY . .

RUN g++ -std=c++17 main.cpp -o app -pthread

EXPOSE 8080

CMD ["./app"]