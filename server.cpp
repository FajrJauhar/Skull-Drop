#include <iostream>
#include <unistd.h>           // for close()
#include <string.h>           // for memset()
#include <sys/socket.h>       // for socket(), bind(), listen(), accept()
#include <netinet/in.h>       // for sockaddr_in
#include <arpa/inet.h>        // for htons()

using namespace std;

int main() {
    // Step 1: Create socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        perror("Socket creation failed");
        return 1;
    }

    // Step 2: Define address
    sockaddr_in serverAddress;
    memset(&serverAddress, 0, sizeof(serverAddress)); // optional zeroing
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080); // port number
    serverAddress.sin_addr.s_addr = INADDR_ANY; // listen on all interfaces

    // Step 3: Bind socket
    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        perror("Bind failed");
        close(serverSocket);
        return 1;
    }

    // Step 4: Listen for connections
    if (listen(serverSocket, 5) < 0) {
        perror("Listen failed");
        close(serverSocket);
        return 1;
    }

    cout << "[*] Server listening on port 8080...\n";

    while (true) {
        // Step 5: Accept a connection
        int clientSocket = accept(serverSocket, nullptr, nullptr);
        if (clientSocket < 0) {
            perror("Accept failed");
            continue;
        }
cout << "[+] Connection accepted.\n";

        // Step 6: Receive data
        char buffer[1024] = {0};
        ssize_t bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived > 0) {
            cout << "Message from client: " << buffer << endl;
        } else {
            cerr << "Receive failed or client disconnected.\n";
        }

        // Step 7: Close client connection
        close(clientSocket);
        cout << "[-] Connection closed.\n";
    }

    // Step 8: Close server socket
    close(serverSocket);
    return 0;
}
