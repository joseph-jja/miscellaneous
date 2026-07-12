pub mod iface {
    use network_interface::{NetworkInterface, NetworkInterfaceConfig};
  
    use crate::utils::utils::utils::LINE_ENDING;

    use gethostname::gethostname;

    pub fn get_interfaces() -> String {
        // Retrieve all network interfaces on the system
        let interfaces = NetworkInterface::show().expect("Failed to load network interfaces");
 
        let os_hostname: String = gethostname(); // TODO get this as string
        
        let mut network_info: String = String::from("");
        for interface in interfaces {
            let iface_name: String = interface.name.to_string();
            if !iface_name.starts_with("lo") && !iface_name.starts_with("dummy") { 
                network_info.push_str(&iface_name);
    
                // Loop through all associated IP addresses (IPv4 and IPv6)
                network_info.push_str(":");
                for addr in interface.addr {
                    if addr.ip().is_ipv4() {
                        network_info.push_str(" ");
                        // TODO only use last digit
                        network_info.push_str(&addr.ip().to_string());
                    }
                }
                network_info.push_str(LINE_ENDING);
            }
        }
        return network_info.replace("\"", "");
    }
}
