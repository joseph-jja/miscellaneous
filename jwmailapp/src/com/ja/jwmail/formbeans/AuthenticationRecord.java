package com.ja.jwmail.formbeans;


/**
 * class that contains the fields needed to authenticate a user
 * 
 * @author Joseph Acosta
 */
public class AuthenticationRecord extends BaseFormBean { 

    private String username;
    private String password;
    
    private String pop3MailServer;
    private String smtpMailServer;
    private String maildomainname;
    
    private boolean tls = false;
    private boolean ssl = false;
    private boolean apop = false;
    private boolean smtpauth = false;
    private int smtpPort = 25;
    private int pop3Port = 110;
    
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
	 * @param pop3MailServer the pop3MailServer to set
	 */
	public void setPop3MailServer(String pop3MailServer) {
		this.pop3MailServer = pop3MailServer;
	}
	/**
	 * @return the pop3MailServer
	 */
	public String getPop3MailServer() {
		return pop3MailServer;
	}
	/**
	 * @param smtpMailServer the smtpMailServer to set
	 */
	public void setSmtpMailServer(String smtpMailServer) {
		this.smtpMailServer = smtpMailServer;
	}
	/**
	 * @return the smtpMailServer
	 */
	public String getSmtpMailServer() {
		return smtpMailServer;
	}
	/**
	 * @param apop the apop to set
	 */
	public void setApop(boolean apop) {
		this.apop = apop;
	}
	/**
	 * @return the apop
	 */
	public boolean isApop() {
		return apop;
	}
	/**
	 * @param smtpPort the smtpPort to set
	 */
	public void setSmtpPort(int smtpPort) {
		this.smtpPort = smtpPort;
	}
	/**
	 * @return the smtpPort
	 */
	public int getSmtpPort() {
		return smtpPort;
	}
	/**
	 * @param pop3Port the pop3Port to set
	 */
	public void setPop3Port(int pop3Port) {
		this.pop3Port = pop3Port;
	}
	/**
	 * @return the pop3Port
	 */
	public int getPop3Port() {
		return pop3Port;
	}
	/**
	 * @param tls the tls to set
	 */
	public void setTls(boolean tls) {
		this.tls = tls;
	}
	/**
	 * @return the tls
	 */
	public boolean isTls() {
		return tls;
	}
	/**
	 * @param ssl the ssl to set
	 */
	public void setSsl(boolean ssl) {
		this.ssl = ssl;
	}
	/**
	 * @return the ssl
	 */
	public boolean isSsl() {
		return ssl;
	}
	/**
	 * @param smtpauth the smtpauth to set
	 */
	public void setSmtpauth(boolean smtpauth) {
		this.smtpauth = smtpauth;
	}
	/**
	 * @return the smtpauth
	 */
	public boolean isSmtpauth() {
		return smtpauth;
	}
	/**
	 * @param maildomainname the maildomainname to set
	 */
	public void setMaildomainname(String maildomainname) {
		this.maildomainname = maildomainname;
	}
	/**
	 * @return the maildomainname
	 */
	public String getMaildomainname() {
		return maildomainname;
	}

}

