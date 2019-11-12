const baseDir = process.cwd();

const request = require('https').request;

const API_ENDPOINT = 'https://api.weather.gov/';

const latitude = '37.762626', 
     longitude = '-122.435291';

const DISCOVER = `${API_ENDPOINT}/points/${latitude},${longitude}`;



