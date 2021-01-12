// simple wrapper around promises
module.exports = promiseIn => (
    promiseIn.then(data => ([undefined, data])).catch(msg => ([msg, undefined]))
);

