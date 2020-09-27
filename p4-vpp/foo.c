                        /* construct key */
                        struct pkt_filter4_0_key key = {};
                        key.field0 = hdr.ipv4.srcAddr;
                        key.field1 = hdr.ipv4.dstAddr;
                        key.field2 = hdr.ipv4.protocol;
                        key.field3 = hdr.ipv4.diffServ;
                        key.field4 = meta->_acl_l4srcPort3;
                        key.field5 = meta->_acl_l4dstPort4;
                        /* value */
                        struct pkt_filter4_0_value *value = NULL;
                        /* perform lookup */
                        ubpf_map_lookup(&pkt_filter4_0, &key);

                        if (value != NULL) {
                            /* run action */
                            switch (value->action) {
                                case drop4: 
                                {
                                }
                                break;
                                case permit4: 
                                {
                                    meta->_acl_log13 = (uint8_t)value->u.permit4.abits;
                                    meta->_acl_gate_open15 = (uint8_t)value->u.permit4.abits >> 1;
                                    meta->_acl_gate_dir14 = (uint8_t)value->u.permit4.abits >> 2;
                                    meta->_acl_mirror16 = (uint8_t)value->u.permit4.abits >> 3;
                                    meta->_acl_chk_credit17 = (uint8_t)value->u.permit4.abits >> 4;
                                    meta->_acl_chk_max_bw_exceed18 = (uint8_t)value->u.permit4.abits >> 5;
                                    meta->_acl_block19 = (uint8_t)value->u.permit4.abits >> 6;
                                    meta->_acl_outer20 = (uint8_t)value->u.permit4.abits >> 7;
                                    meta->_acl_outer_desc1 = value->u.permit4.outer_desc;
                                    meta->_acl_ig_strip2 = value->u.permit4.ig_strip;
                                    meta->_acl_outer_info_teid6 = value->u.permit4.teid;
                                    meta->_acl_outer_info_dstPort11 = value->u.permit4.dstPort;
                                    meta->_acl_filt_dir26 = value->u.permit4.filt_dir;
                                    meta->_acl_reflec_qos24 = value->u.permit4.reflec_qos;
                                    meta->_acl_outer_info_ip7 = value->u.permit4.ip;
                                    meta->_acl_outer_info_src_ip8 = value->u.permit4.src_ip;
                                }
                                break;
                                case add_eth4: 
                                {
                                    meta->_acl_log13 = (uint8_t)value->u.add_eth4.abits;
                                    meta->_acl_gate_open15 = (uint8_t)value->u.add_eth4.abits >> 1;
                                    meta->_acl_gate_dir14 = (uint8_t)value->u.add_eth4.abits >> 2;
                                    meta->_acl_mirror16 = (uint8_t)value->u.add_eth4.abits >> 3;
                                    meta->_acl_chk_credit17 = (uint8_t)value->u.add_eth4.abits >> 4;
                                    meta->_acl_chk_max_bw_exceed18 = (uint8_t)value->u.add_eth4.abits >> 5;
                                    meta->_acl_block19 = (uint8_t)value->u.add_eth4.abits >> 6;
                                    meta->_acl_outer20 = (uint8_t)value->u.add_eth4.abits >> 7;
                                    meta->_acl_ig_strip2 = value->u.add_eth4.ig_strip;
                                                                        hdr.ethernet.cgen_valid = 1;
                                    hdr.ethernet.srcAddr = value->u.add_eth4.srcAddr;
                                    hdr.ethernet.dstAddr = value->u.add_eth4.dstAddr;
                                    hdr.ethernet.etherType = value->u.add_eth4.etherType;
                                }
                                break;
                                default: return 1;
                            }
                        }
                        else return 1;
                    }
