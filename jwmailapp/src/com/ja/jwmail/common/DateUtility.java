package com.ja.jwmail.common;

import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeSupport;
import java.util.Calendar;
import java.util.Date;

/**
 * This was taken in part from
 * the examples/dates/calendar bean that came with tomcat 3.2.1
 * It was stripped out and only the calendar date that we want to show
 * has been kept.
 *
 * This class shows todays date in the format of Month, Day, Year.
 *
 * This class extends Date and uses the toString Method to
 * return the actual date.
 */
public class DateUtility extends Date {

	private static final String SHOWDATE_PROPERTY = "ShowDateProperty";

	private PropertyChangeSupport ShowDatePropertySupport;

	private String dateTimeStamp;

	// a String array containing all the months
	private static String[] months = new String [] {
		"January", "February", "March",
		"April", "May", "June",
		"July", "August", "September",
		"October", "November", "December" };

	// our calendar object
	private Calendar calendar = null;

	private Date calendarTime = null;

	/***********************************************
	 * Description:
	 *   This is the constructor. This method extends
	 *   the date object.
	 **********************************************/
	public DateUtility() {
		calendar = Calendar.getInstance();
		this.calendarTime = new Date();
		calendar.setTime(calendarTime);
	}

	public void setDateTime(String newCalTime ) {

		String oldValue = dateTimeStamp;
		dateTimeStamp = newCalTime;
		ShowDatePropertySupport.firePropertyChange(SHOWDATE_PROPERTY, oldValue, dateTimeStamp);
		//this.calendarTime = new Date(newCalTime);
	}

	public String getDateProperty() {
		return this.toString();
	}

	public void addPropertyChangeListener(PropertyChangeListener listener) {
		ShowDatePropertySupport.addPropertyChangeListener(listener);
	}

	public void removePropertyChangeListener(PropertyChangeListener listener) {
		ShowDatePropertySupport.removePropertyChangeListener(listener);
	}


	/***********************************************
	 * Description:
	 *   This overides the parents toString method
	 *   and returns the date string formatted for us.
	 *
	 *  Returns:
	 *   @return Sting which contains the date formatted
	 *           in with the full month name, the date, and a
	 *           four diget year.
	 *
	 **********************************************/
	public String toString() {
		return months[calendar.get(Calendar.MONTH)] + " " +  calendar.get(Calendar.DAY_OF_MONTH) + ", " + calendar.get(Calendar.YEAR);
	}

}
