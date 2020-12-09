An overview of prior P4-16 extensions (`P4++`) is provided in `../p4-code-reuse/ansible.md`. p4-cripser is akin to DNA cleaver technology called CRISPER and
helps cleave P4 code at desired locations.

# New Extension(s) 

## New keyword `cleave`

Cleaving involves removing the object and once all cleaving is completed
the leftover P4 program and its control plane is dumped to files.

Examples for how the `cleave` keyword is used are provided below.

```p4
struct headers_t cleave { // tells compiler to cleave this struct
    new_header_t new_header;
}

parser parserA(…) cleave { // tells compiler to cleave parser
    ...
}

parser parserB(…) {
    state parse_ethernet {
        packet.extract(hdr.ethernet);
        transition select(hdr.ethernet.etherType) {
            16w0x8100: parse_vlan;
            16w0x88a8: parse_qinq;
            16w0x8847: parse_mpls cleave; // cleave statement
            16w0x800:  parse_ipv4;
            16w0x86dd: parse_ipv6;
            default: accept;
        }
    }

    state parse_mpls cleave { // tells compiler to remove parser state for MPLS.
	    // No need to remove parse_mpls_bos because its an unused state.
        packet.extract(hdr.mpls.next);
        transition select(hdr.mpls.last.bos) {
            1w1: parse_mpls_bos;
            default: parse_mpls;
        }
    }
    state parse_mpls_bos {
        transition select((packet.lookahead<bit<4>>())[3:0]) {
            4w0x4: parse_mpls_ipv4;
            4w0x6: parse_mpls_ipv6;
            default: reject;
        }
    }

}

control ingress(...) cleave { // tells compiler to remove this control
  ...
}

control foo(...) {
    action boo(...) cleave { // action not tied to any table is removed.
	}
	
	action woo(... ) {}

	table moo cleave { // remove table, its action woo(), table invocation in apply block.
	    key = {}
		action = { woo; }
	}
	apply {
	    moo.apply();
	}
}

## deparser()

The deparser has no impact because any header cleaved is inValid and not emitted.


```
