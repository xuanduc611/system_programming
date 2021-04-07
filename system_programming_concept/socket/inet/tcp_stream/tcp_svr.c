#include "tcp_stream_hdr.h"

#define BACKLOG     50

int main(int argc, char** argv)
{
    uint32_t                seq_num;
    uint8_t                 req_len_str[INT_LEN];   // Requested sequence's length
    uint8_t                 seq_num_str[INT_LEN];   // Start of returned sequence
    struct sockaddr_storage claddr;
    uint16_t                lfd, cfd, optval, req_len;
    socklen_t               addr_len;
    struct addrinfo         hints;
    struct addrinfo         *result;
    struct addrinfo         *rp;
}