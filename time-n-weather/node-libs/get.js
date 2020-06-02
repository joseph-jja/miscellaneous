const baseDir = process.cwd();

const httpsRequest = require('https').request;

const USER_AGENT = `"Nozilla/1.0 (console; pios x86_64 ${process.version}) AppleWebKit/537.36 (KHTML, like Gecko but not) xpi/70.1.1`;

function getOptions(host, urlpath) {
    const options = {
        hostname: host,
        port: 443,
        path: urlpath,
        method: 'GET',
        headers: {
            'User-Agent': USER_AGENT
        }
    };
    return options;
}

async function request(options) {

    return new Promise((resolve, reject) => {

        const req = httpsRequest(options, (res) => {
            //  console.log('statusCode:', res.statusCode);
            //  console.log('headers:', res.headers);

            const chunks = [];
            res.on('data', (d) => {
                chunks.push(d);
            });

            res.on('error', (e) => {
                console.error(e);
                reject(e);
            });
            res.on('end', () => {
                try {
                    const results = JSON.parse(Buffer.concat(chunks));

                    resolve(results);
                } catch (e) {
                    reject(e);
                }
            });
        });

        req.on('error', (e) => {
            console.error(e);
            reject(e);
        });
        req.end();
    });
}


module.exports = {
    getOptions,
    request
};