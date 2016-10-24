"use strict";

var JEchartsOption = function (chart, channel, option) {
    //
    var echartsOption = this;
    this.chart = chart;
    this.channel = channel;
    this.option = option;

    // title
    option.titleChanged.connect(function (value) {
        chart.setOption({title:{text:value}});
    });
    // color
    option.colorChanged.connect(function (value) {
        chart.setOption({color:value});
    });
    // backgroundColor
    option.backgroundColorChanged.connect(function (value) {
        chart.setOption({backgroundColor:value});
    });
    // animation
    option.animationChanged.connect(function (value) {
        chart.setOption({animation:value});
    });
    // animationDuration
    option.animationDurationChanged.connect(function (value) {
        chart.setOption({animationDuration:value});
    });
    //
};

//required for use with nodejs
if (typeof module === 'object') {
    module.exports = {
        JEchartsOption: JEchartsOption
    };
}