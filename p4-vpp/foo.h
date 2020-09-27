struct pkt_filter4_0_key {
    uint32_t field1; /* hdr.ipv4.dstAddr */
    uint32_t field0; /* hdr.ipv4.srcAddr */
    uint16_t field5; /* meta._acl_l4dstPort4 */
    uint16_t field4; /* meta._acl_l4srcPort3 */
    uint8_t field3; /* hdr.ipv4.diffServ */
    uint8_t field2; /* hdr.ipv4.protocol */
};
enum pkt_filter4_0_actions {
    drop4,
    permit4,
    add_eth4,
};
struct pkt_filter4_0_value {
    enum pkt_filter4_0_actions action;
    union {
        struct {
        } drop4;
        struct {
            uint8_t abits;
            uint16_t ig_strip;
            uint16_t outer_desc;
            uint32_t teid;
            uint32_t ip;
            uint32_t src_ip;
            uint16_t dstPort;
            uint8_t filt_dir;
            uint8_t reflec_qos;
        } permit4;
        struct {
            uint8_t abits;
            uint16_t ig_strip;
            uint64_t srcAddr;
            uint64_t dstAddr;
            uint16_t etherType;
        } add_eth4;
    } u;
};
