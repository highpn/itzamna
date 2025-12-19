#pragma once
#include <stdint.h>
#include <stdbool.h>

typedef struct {
	int sockfd;
	// Other fields for state
} NetConnection;

// Initialization and shutdown
bool net_init(void);
void net_shutdown(void);

// TCP connections
NetConnection *net_connect_tcp(const char *host, uint16_t port);
void net_disconnect(NetConnection *conn);

// UDP sockets
NetConnection *net_create_udp(uint16_t port);
void net_send_udp(NetConnection *conn, const void *data, size_t size, const char *host, uint16_t port);

// Data send/receive
bool net_send(NetConnection *conn, const void *data, size_t size);
int net_receive(NetConnection *conn, void *buffer, size_t max_size);
// Utility functions
bool net_is_connected(NetConnection *conn);
void net_set_timeout(NetConnection *conn, int timeout_ms);
int net_get_last_error(void);
void net_clear_last_error(void);
const char *net_strerror(int err_code);
void net_print_connection_info(NetConnection *conn);
void net_print_network_stats(void);
void net_reset_network_stats(void);
void net_update(void);
// DNS resolution
bool net_resolve_hostname(const char *hostname, char *ip_buffer, size_t buffer_size);
// Multicast support
NetConnection *net_join_multicast_group(const char *multicast_ip, uint16_t port);
void net_leave_multicast_group(NetConnection *conn);
// IPv6 support
NetConnection *net_connect_tcp_ipv6(const char *host, uint16_t port);
NetConnection *net_create_udp_ipv6(uint16_t port);
// SSL/TLS support
bool net_enable_tls(NetConnection *conn);
void net_disable_tls(NetConnection *conn);
// Network interface information
void net_list_network_interfaces(void);
// Bandwidth management
void net_set_bandwidth_limit(NetConnection *conn, size_t max_bytes_per_sec);
size_t net_get_bandwidth_usage(NetConnection *conn);
// Packet fragmentation and reassembly
bool net_enable_fragmentation(NetConnection *conn, size_t mtu);
void net_disable_fragmentation(NetConnection *conn);
// NAT traversal
bool net_enable_nat_traversal(NetConnection *conn);

void net_disable_nat_traversal(NetConnection *conn);
// Quality of Service (QoS)
bool net_set_qos(NetConnection *conn, int dscp_value);
int net_get_qos(NetConnection *conn);
// Network diagnostics
void net_run_diagnostics(NetConnection *conn);
void net_print_diagnostics_report(NetConnection *conn);
// Callback registration
typedef void (*net_data_received_callback)(NetConnection *conn, const void *data, size size_t size, void *user_data);

void net_register_data_received_callback(NetConnection *conn,
                                         net_data_received_callback callback,
                                         void *user_data);
void net_unregister_data_received_callback(NetConnection *conn);