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

```
The Ping command generates Address Resolution Protocol (ARP) packets.It also generates Internet Control Message Protocol (ICMP) packets. ICMP is a network layer protocol that reports errors and provides other information relevant to IP packet processing. ICMP is used by the ping command to test an IP network connection. 
```


</details>
<details>
    <summary>What are the MAC and IP addresses of the ping packets?</summary>

```
The MAC and IP addresses of the ping packets are the same as the computers that are communicating. 
```
![EXP2 GNU3-GNU4](images/pingMACIP.png)

</details>
<details>
    <summary>How to determine if a receiving Ethernet frame is ARP, IP, ICMP</summary>

```
It is possible to determine if a receiving Ethernet frame is ARP, IP, ICMP by checking WireShark capture, in Portocol column. This protocol is usually placed in the first 2 bytes of the Ethernet frame. 
``` 

</details>
<details>
    <summary>How to determine the length of a receiving frame?</summary>

```
It is possible to determine the length of a receiving frame by checking WireShark capture, in Length column. 
```
</details>
<details>
    <summary>What is the loopback interface and why is it important</summary>

```
The loopback interface is a virtual interface that is always up and available after the operating system has booted. It is used to communicate with the operating system itself. It is important because it is used to test the network software without the need for any hardware network interfaces. With this, it is possible to periodically check if the connections are working properly. 
```
</details>

# Exp 3

## Lab

| PC    | eth  | ip            | mac               |
| ----- | ---- | ------------- | ----------------- |
| gnu64 | eth0 | 172.16.60.254 | 00:21:5a:5a:75:bb |
| gnu64 | eth1 | 172.16.61.253 | 00:08:54:71:73:ed |



<details>
    <summary>How to configure bridge60? </summary>


```bash
Bridge60 is configured with the following commands:


/interface bridge add name=bridge60
/interface bridge port remove [find interface=ether9] 
/interface bridge port remove [find interface=ether17]
/interface bridge port add bridge=bridge60 interface=ether9
/interface bridge port add bridge=bridge60 interface=ether17
/interface bridge port add bridge=bridge50 interface=ether9
/interface bridge port add bridge=bridge50 interface=ether17 


This made it possible to connect the two computers(TUX3 and TUX4) to the same network,forming a smaller network. 
```

</details>
<details>
    <summary>How many broadcast domains are there? How can you conclude it from the logs?</summary>

```
Since we configured 2 bridges, we can conclude that there are 2 broadcast domains. This is because each bridge is a broadcast domain. We can conclude this from the logs because TUX3 obtained a response from TUX4, but not from TUX2. This means that TUX3 is in the same broadcast domain as TUX4, but not in the same broadcast domain as TUX2.
```

</details>