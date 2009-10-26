#include "checksum.h"
#include <string.h>
/* Add up checksum, return value will be filled in checksum filed in header */
u_short add_checksum(u_short len_udp,
		     int padding, const u_short *temp)
{
  u_short prot_udp = 17;
  u_short padd = 0;
  u_short word16;
  u_long sum;
  static u_char buff[1600];
  int i;
  memset(buff, 0, 1600);
  memcpy(buff, temp, len_udp);
  //cout << "len_udp " << len_udp << endl;
  // Find out if the length of data is even or odd number. If odd,
  // add a padding byte = 0 at the end of packet
  if ((padding & 1) == 1)
    {
      padd = 1;
      buff[len_udp] = 0;
    }

  //initialize sum to zero
  sum = 0;

  // make 16 bit words out of every two adjacent 8 bit words and
  // calculate the sum of all 16 vit words
  for (i = 0; i < len_udp + padd; i = i + 2)
    {
      word16 = ((buff[i] << 8) & 0xFF00) + (buff[i + 1] & 0xFF);
      //cout << hex << (int) buff[i] << " " << (int) buff[i + 1] << " ";
      sum = sum + (unsigned long) word16;
    }
  //cout << "data sum" << hex << sum << endl;
  // add the UDP pseudo header which contains the IP source and destinationn addresses
  // for (i = 0; i < 4; i = i + 2)
  //   {
  //     //cout << inet_ntoa(*(in_addr*) src_addr) << endl;
  //     word16 = ((src_addr[i] << 8) & 0xFF00) + (src_addr[i + 1] & 0xFF);
  //     sum = sum + word16;
  //   }
  //cout << "data sum" << hex << sum << endl;
  // for (i = 0; i < 4; i = i + 2)
  //   {
  //     //cout << inet_ntoa(*(in_addr*) dest_addr) << endl;
  //     word16 = ((dest_addr[i] << 8) & 0xFF00) + (dest_addr[i + 1] & 0xFF);
  //     sum = sum + word16;
  //   }
  //cout << "data sum" << hex << sum << endl;
  // the protocol number and the length of the UDP packet
  //sum = sum + prot_udp + len_udp;
  // keep only the last 16 bits of the 32 bit calculated sum and add the carries
  //cout << "data sum" << hex << sum << endl;
  while (sum >> 16)
    sum = (sum & 0xFFFF) + (sum >> 16);
  //cout << "data sum" << hex << sum << endl;
  // Take the one's complement of sum
  sum = ~sum;

  return ((u_short) sum);
	
}



