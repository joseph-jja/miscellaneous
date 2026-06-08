pub fn current_position_string() -> &'static RwLock<String> {
    static STRING_LOCK: OnceLock<RwLock<String>> = OnceLock::new();
    STRING_LOCK.get_or_init(|| RwLock::new(String::from("")))
}

pub mod buffer_utils {}
