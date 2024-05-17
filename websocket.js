import ws from 'k6/ws';
import { check } from 'k6';
// k6 run -u 100  ./websocket.js
export let options = {
    vus: 10, // 同时运行的虚拟用户数量
    duration: '30s', // 测试持续时间，这里设置为60秒
};
export default function () {
    const url = 'ws://127.0.0.1:9090/echo?room_name=001'; // WebSocket URL
    const params = { tags: { my_tag: 'websocket' } };

    const message = JSON.stringify({
        "key": "aa",
       /* "Name": "Liming",
        "Age": 26,
        "Language": [
            "C++",
            "Java"
        ],
        "E-mail": {
            "Netease": "lmshao@163.com",
            "Hotmail": "liming.shao@hotmail.com"
        }*/
    });

    const res = ws.connect(url, params, function (socket) {
        socket.on('open', function open() {
            console.log('connected');
            socket.send(message);
        });

        socket.on('message', function (data) {
            //console.log('Message received:', data);
            socket.send(message);
        });

        socket.on('close', function () {
            console.log('disconnected');
        });
    });

    check(res, { 'status is 101': (r) => r && r.status === 101 });
}
