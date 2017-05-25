#include "ServerThread.hpp"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void ServerThread::run()
{
	std::cout << __FILE__ << " " <<__FUNCTION__ << ": " << "i was started" << std::endl;

	connectToServer();

	while (true) {
		if (buffer->empty())
			buffer->lockServerThread();

		std::cout << __FILE__ << __FUNCTION__ << ": " << "i am running" << std::endl;

		if (!buffer->empty())
			buffer->popFront();

	}
}

void ServerThread::connectToServer()
{
	socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);

 	if (socketDescriptor < 0)
 		throw std::runtime_error("ServerThread cannot open socket");

	sockaddr_in socketData;
	socketData.sin_family = AF_INET;
	inet_aton(configuration->getServerAddress(), &socketData.sin_addr);
	socketData.sin_port = htons(configuration->getServerPort());



   /* Now connect to the server */
   if (connect(socketDescriptor, (struct sockaddr*)&socketData, sizeof(socketData)) < 0)
		throw std::runtime_error("Server connection error");

   /* Now ask for a message from the user, this message
      * will be read by server
   */
	// int n;
   // printf("Please enter the message: ");
   // bzero(buffer,256);
   // fgets(buffer,255,stdin);
   //
   // /* Send message to the server */
   // n = write(sockfd, buffer, strlen(buffer));
   //
   // if (n < 0) {
   //    perror("ERROR writing to socket");
   //    exit(1);
   // }
   //
   // /* Now read server response */
   // bzero(buffer,256);
   // n = read(sockfd, buffer, 255);
   //
   // if (n < 0) {
   //    perror("ERROR reading from socket");
   //    exit(1);
   // }
   //
   // printf("%s\n",buffer);
}
