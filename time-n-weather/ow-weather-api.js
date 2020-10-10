const baseDir = process.cwd();

const os = require('os'),
    fs = require('fs'),
    {
        promisify
    } = require('util');

const {
    getOptions,
    request
} = require(`${baseDir}/node-libs/get`);

const readFile = promisify(fs.readFile);

const latitude = '37.7464',
    longitude = '-122.4442';

const API_HOSTNAME = 'api.openweathermap.org',
    DISCOVER_ENDPOINT = `/data/2.5/weather?lat=${latitude}&lon=${longitude}`;

const RELOAD = 1000 * 60 * 60;


function toFahrenheit(kelvin) {
    return `${Math.round(9 / 5 * kelvin - 459.67)}F`;
}

async function start() {

    //const results = require('/tmp/full.js');
    const keyFile = await readFile(`${baseDir}/config.json`);
    key = JSON.parse(keyFile.toString()).key;

    const options = getOptions(API_HOSTNAME, DISCOVER_ENDPOINT);
    options.path += `&APPID=${key}`;

    const results = await request(options);
    const main = results.main;

    const updateTime = new Date(), 
        formattedDate = `${updateTime.getFullYear()}-${updateTime.getMonth() + 1}-${updateTime.getDate()}`, 
        formattedTime = `${updateTime.getHours()}:${updateTime.getMinutes() + 1}`;

    const updated = `Last Updated: ${formattedDate} @ ${formattedTime}`;
    const temp = `Current: ${toFahrenheit(main.temp)}`;
    const tempMin = toFahrenheit(main.temp_min);
    const tempMax = toFahrenheit(main.temp_max);

    const tempRange = `High/Low: ${tempMax}/${tempMin}`;
    const humidity = `Humidity: ${main.humidity}%`;
    const cloudy = `Clouds: ${results.clouds['all'] || 0}%`;
    const rain = `Rain: ${results.rain && results.rain['1h'] || 0} / ${results.rain && results.rain['3h'] || 0}`;

    const data = `${temp}    ${tempRange}${os.EOL}${humidity}    ${cloudy}    ${rain}${os.EOL}${updated}`;

    fs.writeFile('/tmp/details.txt', data, () => {});
    fs.writeFile('/tmp/full.js', `module.exports = ${JSON.stringify(results)};`, () => {});

}

start();
setInterval(() => {
    start();
}, RELOAD);
