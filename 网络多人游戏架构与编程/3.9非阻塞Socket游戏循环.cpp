void DoGameLoop()
{
    UDPSocketPtr mySock = SocketUtil::CreateUDPSocket(INET);
    mySock->SetNonBlockingMode(true);

    while(gIsGameRunning)
    {
        char data[1500];
        SocketAddress socketAddress;

        int bytesReceived = mySock->ReceiveFrom(data, sizeof(data), socketAddress);
        if (bytesReceived > 0)
        {
            ProcessReceivedData(data, bytesReceived, socketAddress);
        }
        DoGameFrame();
    }
}