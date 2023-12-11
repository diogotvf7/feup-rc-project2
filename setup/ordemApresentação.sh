/system reset-configuration  no routermtik e no mtik
No TUX63:
$ ifconfig eth0 up
$ ifconfig eth0 172.16.60.1/24

No TUX63:
$ ifconfig eth0 up
$ ifconfig eth0 172.16.60.254/24

No TUX62:
$ ifconfig eth0 up
$ ifconfig eth0 172.16.61.1/24

No Switch:

> /interface bridge add name=bridge60
> /interface bridge add name=bridge61

> /interface bridge port remove [find interface=ether1] TUX62
> /interface bridge port remove [find interface=ether9] TUX63
> /interface bridge port remove [find interface=ether17] TUX64

> /interface bridge port add bridge=bridge61 interface=ether1
> /interface bridge port add bridge=bridge60 interface=ether9
> /interface bridge port add bridge=bridge60 interface=ether17

No TUX64:

$  ifconfig eth1 up
$  ifconfig eth1 172.16.61.253/24

No switch:

> /interface bridge port remove [find interface=ether15]
> /interface bridge port add bridge=bridge61 interface=ether15

No TUX64:

sysctlnet.ipv4.ip_forward=1
sysctlnet.ipv4.icmp_echo_ignore_broadcasts=0

No TUX62:

route add -net  172.16.60.0/24 gw 172.16.61.253

No TUX63:

route add -net  172.16.61.0/24 gw 172.16.60.254


Ligar eth1 do router à 6.1 da régua, eth2  do router ao switch

   /interface bridge port remove [find interface=ether5]
   /interface bridge port add bridge=bridge61 interface=ether5


Trocar o cabo ligado a consola do Switch para o Router MT

   /ip address add address=172.16.2.69/24 interface=ether1
   /ip address add address=172.16.61.254/24 interface=ether2


No tux62:

    route add default gw 172.16.61.254

No tux63:
    
    route add default gw 172.16.60.254

No tux64:
        
    route add default gw 172.16.61.254

No router MT:

   /ip route add dst-address=172.16.60.0/24 gateway=172.16.61.253
   /ip route add dst-address=0.0.0.0/0 gateway=172.16.2.254 

No Tux62:
    
    sysctl net.ipv4.conf.eth0.accept_redirects=0 
    sysctl net.ipv4.conf.all.accept_redirects=0 
    route del -net 172.16.60.0 gw 172.16.61.253 netmask 255.255.255.0
    traceroute -n
    route add -net 172.16.60.0/24 gw 172.16.61.253
    sysctl net.ipv4.conf.eth0.accept_redirects=0 
    sysctl net.ipv4.conf.all.accept_redirects=0 

No router MT:

    /ip firewall nat disable 0

    /ip firewall nat enable 0


todos os tuxs:
    sudo nano /etc/resolv.conf
    escrever 'nameserver 172.16.2.1'


Conectar 5.1 com o E0 do Tux53;

Em Tux53 executar os seguintes comandos:

    $ ifconfig eth0 172.16.2.63/24
    $ route add default gw 172.16.2.254