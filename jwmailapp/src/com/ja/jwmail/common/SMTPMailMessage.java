package com.ja.jwmail.common;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class SMTPMailMessage {

	private List<String> toUsers = new ArrayList<String>();
	private List<String> ccUser = new ArrayList<String>();
	private List<String> bccUser = new ArrayList<String>();
	private String fromUser;
	
	private String subject;
	private String message;
	
	private boolean smtpAuth = false;
	private String username; 
	private String password;
	private boolean usetls = false; 
	private boolean usessl = false;
	
	private List<Pair<String, String>> attachments;
	
	/**
	 * @param toUsers the toUsers to set
	 */
	public void setToUsers(List<String> toUsers) {
		this.toUsers = toUsers;
	}
	/**
	 * @return the toUsers
	 */
	public List<String> getToUsers() {
		return toUsers;
	}
	/**
	 * @param ccUser the ccUser to set
	 */
	public void setCcUser(List<String> ccUser) {
		this.ccUser = ccUser;
	}
	/**
	 * @return the ccUser
	 */
	public List<String> getCcUser() {
		return ccUser;
	}
	/**
	 * @param bccUser the bccUser to set
	 */
	public void setBccUser(List<String> bccUser) {
		this.bccUser = bccUser;
	}
	/**
	 * @return the bccUser
	 */
	public List<String> getBccUser() {
		return bccUser;
	}
	/**
	 * @param fromUser the fromUser to set
	 */
	public void setFromUser(String fromUser) {
		this.fromUser = fromUser;
	}
	/**
	 * @return the fromUser
	 */
	public String getFromUser() {
		return fromUser;
	}
	/**
	 * @param subject the subject to set
	 */
	public void setSubject(String subject) {
		this.subject = subject;
	}
	/**
	 * @return the subject
	 */
	public String getSubject() {
		return subject;
	}
	/**
	 * @param message the message to set
	 */
	public void setMessage(String message) {
		this.message = message;
	}
	/**
	 * @return the message
	 */
	public String getMessage() {
		return message;
	}
	/**
	 * @param smtpAuth the smtpAuth to set
	 */
	public void setSmtpAuth(boolean smtpAuth) {
		this.smtpAuth = smtpAuth;
	}
	/**
	 * @return the smtpAuth
	 */
	public boolean isSmtpAuth() {
		return smtpAuth;
	}
	/**
	 * @param username the username to set
	 */
	public void setUsername(String username) {
		this.username = username;
	}
	/**
	 * @return the username
	 */
	public String getUsername() {
		return username;
	}
	/**
	 * @param password the password to set
	 */
	public void setPassword(String password) {
		this.password = password;
	}
	/**
	 * @return the password
	 */
	public String getPassword() {
		return password;
	}
	/**
	 * @param usetls the usetls to set
	 */
	public void setUsetls(boolean usetls) {
		this.usetls = usetls;
	}
	/**
	 * @return the usetls
	 */
	public boolean isUsetls() {
		return usetls;
	}
	/**
	 * @param usessl the usessl to set
	 */
	public void setUsessl(boolean usessl) {
		this.usessl = usessl;
	}
	/**
	 * @return the usessl
	 */
	public boolean isUsessl() {
		return usessl;
	}
	/**
	 * @param attachments the attachments to set
	 */
	public void setAttachments(List<Pair<String, String>> attachments) {
		this.attachments = attachments;
	}
	/**
	 * @return the attachments
	 */
	public List<Pair<String, String>> getAttachments() {
		return attachments;
	}
	
}
