package com.ja.jwmail.formbeans;


public class SMTPRecord extends BaseFormBean {

	private String toUsers;
	private String ccUsers;
	private String bccUsers;
	
	private String subject;
	private String message;
	
	/**
	 * @param toUsers the toUsers to set
	 */
	public void setToUsers(String toUsers) {
		this.toUsers = toUsers;
	}
	/**
	 * @return the toUsers
	 */
	public String getToUsers() {
		return toUsers;
	}
	/**
	 * @param ccUsers the ccUsers to set
	 */
	public void setCcUsers(String ccUsers) {
		this.ccUsers = ccUsers;
	}
	/**
	 * @return the ccUsers
	 */
	public String getCcUsers() {
		return ccUsers;
	}
	/**
	 * @param bccUsers the bccUsers to set
	 */
	public void setBccUsers(String bccUsers) {
		this.bccUsers = bccUsers;
	}
	/**
	 * @return the bccUsers
	 */
	public String getBccUsers() {
		return bccUsers;
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
	
	
}
