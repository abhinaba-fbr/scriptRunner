#!/bin/sh

ip netns add h1
ip netns add h2

ip link add eth0 type veth peer eth1

ip link set eth0 netns h1
ip link set eth1 netns h2

ip netns exec h1 ip link set lo up
ip netns exec h1 ip link set eth0 up
ip netns exec h2 ip link set lo up
ip netns exec h2 ip link set eth1 up

ip netns exec h1 ip address add 10.0.0.1/24 dev eth0
ip netns exec h2 ip address add 10.0.0.2/24 dev eth1

ip netns exec h1 ip link set eth0 down ---set-time 5
ip netns exec h1 ip link set eth0 up ---set-time 10

ip netns exec h1 ping -c 15 10.0.0.2 ---set-time-wait 2