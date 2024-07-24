function WSApi(host = null) {
    const self = this;
    let urlString = window.location.href;
    let url = new URL(urlString);
    // Determine the WebSocket URL based on the current protocol (http or https)
    let wsProtocol = url.protocol === 'https:' ? 'wss:' : 'ws:';
    // Construct the WebSocket URL using the host from the current URL
    const wsUrl = `${wsProtocol}//${url.host}`;
    console.log(wsUrl);
    this.socket = new WebSocket(wsUrl, "web_server");
    this.callbacks = {};
    this.requestId = 0;
    this.id = null;

    this.onmessage = null;

    this.socket.onmessage = msg => {
        const data = JSON.parse(msg.data);

        if (typeof (data) == 'number') {
            self.id = +msg.data;
            self.connected = true;
            //console.log(self.id);
            return;
        }

        if ("id" in data && data.id in self.callbacks) {
            //console.log(data);
            self.callbacks[data.id](data);
        }

        if (this.onmessage) {
            this.onmessage(msg, data);
        }
    }

    this.connect = new Promise((resolve, reject) => {
        this.socket.onopen = () => {
            resolve(self.socket);
        };
        this.socket.onerror = err => {
            console.log(err);
            reject(err);
        }
        this.socket.onclose = event => {
            console.log(event);
        }
    });

    this.connected = false;

    this.connect.then(() => {
        //self.connected = true;
    });
}

WSApi.prototype.sendPostCommand = function (cmd, data, calcVal) {
    console.log(this.id);
    return this.sendCommand(cmd, data, calcVal, true);
}

WSApi.prototype.sendCommand = function (cmd, data, calcVal, isPost = false) {
    let self = this;

    if (self.connected) {
        data.command = cmd;
        data.id = this.requestId;

        if (isPost) {
            $.ajax({
                type: "POST",
                url: `/post/${self.id}`,
                //data: JSON.stringify({command: "mouseClicked", output: output}),
                data: JSON.stringify(data),
                success(res) { console.log(res); },
                //error: function(res) { console.log(res); },
                dataType: "json"
            });
        }
        else {
            this.socket.send(JSON.stringify(data));
        }

        let promise = new Promise((resolve, reject) => {
            self.callbacks[self.requestId] = data => {
                if (calcVal) {
                    resolve(calcVal(data));
                }
                else {
                    resolve(data);
                }
                delete self.callbacks[data.id];
            }
        });
        this.requestId++;
        return promise;
    }
    else {
        return new Promise((resolve, reject) => {
            self.connect.then(() => {
                self.connected = true;
                self.sendCommand(cmd, data, calcVal).then(
                    data => {
                        resolve(data);
                    });
            }
            );
        });
    }

}