void DoTCPLoop()
{
    TCPSocketPtr listenSocket = SocketUtil::CreateTCPSocket(INET);
    SocketAddress receivingAddress(INADDR_ANY, 48000);
    if (listenSocket->Bind(receivingAddress) != NO_ERROR)
    {
        return;
    }
    vector<TCPSocketPtr> readBlockSockets;
    readBlockSockets.push_back(listenSocket);

    vector<TCPSocketPtr> readableSockets;

    while(gIsGameRunning)
    {
        if (SocketUtil::Select(&readBlockSockets, &readableSockets,
                                nullptr, nullptr,
                                nullptr, nullptr))
        {
            // we got a packet-loop through the set ones...
            for(const TCPSocketPtr& socket : readableSockets)
            {
                if (socket == listenSocket)
                {
                    // it's the listen socket, accept a new connection
                    SocketAddress newClientAddress;
                    auto newSocket = listenSocket->Accept(newClientAddress);
                    readBlockSockets.push_back(newSocket);
                    ProcessNewClient(newSocket, newClientAddress);
                }
                else
                {
                    //it's a regular socket-process the data...
                    char segment[GOOD_SEGMENT_SIZE];
                    int dataReceived = socket->Receive(segment, GOOD_SEGMENT_SIZE);
                    if (dataReceived > 0)
                    {
                        ProcessDataFromClient(socket, segment, dataReceived);
                    }
                }
            }
        }
    }
}