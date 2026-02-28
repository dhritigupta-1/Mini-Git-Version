FROM gcc:11

WORKDIR /app

COPY . .

RUN g++ -I.\vcpkg\installed\x64-windows\include server.cpp Repository.cpp -o server.exe -pthread -lws2_32 -lmswsock -L.\vcpkg\installed\x64-windows\lib

EXPOSE 8080

CMD ["./app"]
