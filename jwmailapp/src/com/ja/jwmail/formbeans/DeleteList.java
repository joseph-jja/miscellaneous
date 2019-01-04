package com.ja.jwmail.formbeans;

import java.util.ArrayList;
import java.util.List;

public class DeleteList extends BaseFormBean {

	private List<String> messages;
	private String count;
	
	public DeleteList() {
		this.messages = new ArrayList<String>();
	}
	
	/**
	 * @param messages the messages to set
	 */
	public void setAllMessages(List<String> messages) {
		this.messages = messages;
	}
	/**
	 * @return the messages
	 */
	public List<String> getAllMessages() {
		return messages;
	}
	/**
	 * @param count the count to set
	 */
	public void setCount(String count) {
		this.count = count;
	}
	/**
	 * @return the count
	 */
	public String getCount() {
		return count;
	}
	
	/**
	 * indexed properies things
	 */
	public String getMessages(int index) { 
		return this.messages.get(index);
	}
	
	public void setMessages(int index, String msg) {
		// FIXME!
                               // if the size of messages we have is less than the index to be set
                               // we create all the ones in the middle wiht values of off
                                for ( int i = this.messages.size(); i < index; i+=1 ) { 
                                     this.messages.add("off"); 
                                }
                                // the size of the message list is less than the index
                                // and we know it has been populated up to the index 
                                // from the code above, so then we can just add the element into the list
                                if ( this.messages.size() < index ) { 
		    this.messages.add(msg);
                                } else {
                                    // list size if equal to or greater than index, so we replace at this index
		    this.messages.remove(msg);
		    this.messages.add(index, msg);
                                }
	}	
}
