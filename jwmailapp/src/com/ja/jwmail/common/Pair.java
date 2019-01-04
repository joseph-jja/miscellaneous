package com.ja.jwmail.common;


public class Pair<K, T> {

	private K key;
	private T value;

	public Pair(K k, T v) { 
		this.key = k;
		this.value = v;
	}
	
	/**
	 * @return the key
	 */
	public K getKey() {
		return key;
	}

	/**
	 * @return the value
	 */
	public T getValue() {
		return value;
	}

}
