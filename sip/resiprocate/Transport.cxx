#include <errno.h>

#include <sip2/sipstack/Transport.hxx>

using namespace Vocal2;


Transport::TransportException::TransportException(const std::string& msg, const std::string& file, const int line)
{
}

const char* 
Transport::TransportException::what() const throw()
{
   return "TransportException";
}


Transport::Transport(in_port_t portNum, Fifo<Message>& rxFifo) :
   mPort(portNum), 
   mRxFifo(rxFifo),
   mShutdown(false)
{
}


void
Transport::run()
{
   while(!mShutdown)
   {
      fd_set fdSet; 
      int fdSetSize;

      FD_ZERO(&fdSet); 
      fdSetSize=0;
      FD_SET(mFd,&fdSet); 
      fdSetSize = std::max( mFd+1, fdSetSize );

      int  err = select(fdSetSize, &fdSet, 0, 0, 0);
      int e = errno;
      if (e == 0)
      {
         process();
      }
      else
      {
         assert(0);
      }
   }
}

void
Transport::shutdown()
{
   mShutdown = true;
}

Transport::~Transport()
{
}


