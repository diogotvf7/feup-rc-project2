# Part 2

## Exp 1

### Lab

As the first step of this lab, we have to reset the configuration of the MicroTik router. To do so, we will connect two cables in the following way:

> RS232 -> cisco to gnu64 S0
>
> cisco -> RS232 to MicroTik Console

After this we will set the Baudrate of the serial port to 115200 and press enter on the GTK Term. We run the following command:

```bash
/system reset-configuration
```

Having all the previous configurations reset we are ready to phisically connect the computers `gnu63` and `gnu64` to the same 1

| gnu63                  | gnu64                  |
| ---------------------- | ---------------------- |
| IP: 172.16.60.1        | IP: 172.16.60.254      |
| MAC: 00:22:64:a7:32:ab | MAC: 00:21:5a:5a:75:bb |

### Questions:

<details>
    <summary>What are the commands required to configure this experience?</summary>

```bash
ifconfig eth0 {ip}  # set ip address
ping {ip}           # verify connection between the current computer and the computer with {ip} address
route -n           # show the routing table
arp -a             # show all the entris of the arp table
arp -d {ip}         # delete the entry of the arp table with {ip} address
```

</details>

<details>
    <summary>What are the ARP packets and what are they used for?</summary>
    
```
ARP (Address Resolution Protocol) is a protocol that is used to find the Media Access Control (MAC) address of a network neighbour for a given IPv4 address. This command is used to manipulate or display the kernel's IPv4 network neighbour cache. 
```

</details>

<details>
    <summary>What are the MAC and IP addresses of ARP packets and why?</summary>

In the context of our experience, the IPv4 and MAC addresses of each computer are:

| Computer 1             | Computer 2             |
| ---------------------- | ---------------------- |
| MAC: 00:21:5a:5a:75:bb | MAC: 00:21:5a:61:2d:df |
| IP: 172.16.60.1        | IP: 172.16.60.254      |

| MAC address                                                                                                                                                                                                                                                                                                                                                                                               | IP address                                                                                                                                                                                                                                                                                                                                                                                                                                |
| --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| The MAC (Media Access Control) address is a globally unique identifier that identifies a computer. It is used in the data link layer to ensure the physical address of the computer - this means it is related to the hardware. MAC addresses can't be easily found by third parties, as they are not broadcast over the internet. It is composed of 6 bytes (48 bits) and is represented in hexadecimal. | The IP (Internet Protocol) address identifies a connection between a computer and a network. It can change over time and due to the environment. It is used in the network layer to ensure the logical address of the computer - this means it is related to the software. IP addresses can be easily found by third parties, as they are broadcast over the internet. It is composed of 4 bytes (32 bits) and is represented in decimal. |

</details>
<details>
    <summary>What packets does the ping command generate?</summary>

</details>
<details>
    <summary>What are the MAC and IP addresses of the ping packets?</summary>
</details>
<details>
    <summary>How to determine if a receiving Ethernet frame is ARP, IP, ICMP?</summary>
</details>
<details>
    <summary>How to determine the length of a receiving frame?</summary>
</details>
<details>
    <summary>What is the loopback interface and why is it important</summary>
</details>
