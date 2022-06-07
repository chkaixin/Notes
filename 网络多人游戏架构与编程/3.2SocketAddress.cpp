class SocketAddress
{
public:
    SocketAddress(uint32_t inAddress, uint16_t inPort)
    {
        GetAsSocketAddrIn()->sin_family = AF_INET;
        GetAsSocketAddrIn()->sin_addr.S_un.S_addr = htonl(inAddress);
        GetAsSocketAddrIn()->sin_port = htons(inPort);
    }
    SocketAddress(const sockaddr& inSockAddr)
    {
        memcpy(&mSockAddr, &inSockAddr, sizeof(sockaddr));
    }

    size_t GetSize() const {return sizeof(sockaddr);}

private:
    sockaddr mSockAddr;

    sockaddr_in* GetAsSockAddrIn()
        {return reinterpret_cast<sockaddr_in*>( &mSockAddr );}
};
typedef shared_ptr<SocketAddress> SocketAddressPtr;