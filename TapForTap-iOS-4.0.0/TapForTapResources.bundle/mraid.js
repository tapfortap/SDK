// mraid.js
// This is a local file that will be served when a TFTFreeFormWebView requests mraid.js, rather than loading from the server

window.parent.mraid = {
    
    _screensizeWidth: 0,
    _screensizeHeight: 0,
    _defaultWidth: 0,
    _defaultHeight: 0,
    _isViewable: false,
    _resizeProperties: {},
    _expandProperties: {"isModal": true},
    _placementType: "inline",
    _state: "loading",
    _supports_sms: true,
    _supports_tel: true,
    _supports_calendar: true,
    _supports_store_picture: true,
    _supports_inline_video: true,
    _uses_custom_close: false,
    _currentX: 0,
    _currentY: 0,
    _currentWidth: 0,
    _currentHeight: 0,
    _eventListeners: {'ready': [], 'error': [], 'stateChange': [], 'viewableChange': [], 'sizeChange': []},
    
    addEventListener: function(event, listener) {
        
        if (typeof mraid._eventListeners[event] != 'object') {
            throw 'unknown event type';
        }
        
        mraid._eventListeners[event].push(listener);
        
    },
    
    close : function() {
        window.location = "tapfortap://mraid/close";
    },
    
    createCalendarEvent: function(parameters) {
        
        var argumentString = '';
        if (typeof parameters['id'] == "string") {
            argumentString += "id=" + parameters['id'] + "&";
        }
        if (typeof parameters['description'] == "string") {
            argumentString += "description=" + parameters['description'] + "&";
        }
        if (typeof parameters['location'] == "string") {
            argumentString += "location=" + parameters['location'] + "&";
        }
        if (typeof parameters['summary'] == "string") {
            argumentString += "summary=" + parameters['summary'] + "&";
        }
        if (typeof parameters['start'] == "string") {
            argumentString += "start=" + parameters['start'] + "&";
        }
        if (typeof parameters['end'] == "string") {
            argumentString += "end=" + parameters['end'] + "&";
        }
        if (typeof parameters['status'] == "string") {
            argumentString += "status=" + parameters['status'] + "&";
        }
        if (typeof parameters['transparency'] == "string") {
            argumentString += "transparency=" + parameters['transparency'] + "&";
        }
        if (typeof parameters['recurrence'] == "object") {
            if (typeof parameters['recurrence']['frequency'] == "string") {
                argumentString += "recurrence.frequency=" + parameters['recurrence']['frequency'] + "&";
            }
            if (typeof parameters['recurrence']['daysInWeek'] == "object") {
                argumentString += "recurrence.daysInWeek=" + JSON.stringify(parameters['recurrence']['daysInWeek']) + "&";
            }
            if (typeof parameters['recurrence']['expires'] == "string") {
                argumentString += "recurrence.expires=" + parameters['recurrence']['expires'] + "&";
            }
            if (typeof parameters['recurrence']['start'] == "string") {
                argumentString += "recurrence.start=" + parameters['recurrence']['start'] + "&";
            }
            if (typeof parameters['recurrence']['daysInMonth'] == "object") {
                argumentString += "recurrence.daysInMonth=" + JSON.stringify(parameters['recurrence']['daysInMonth']) + "&";
            }
            if (typeof parameters['recurrence']['monthsInYear'] == "object") {
                argumentString += "recurrence.monthsInYear=" + JSON.stringify(parameters['recurrence']['monthsInYear']) + "&";
            }
            if (typeof parameters['recurrence']['daysInYear'] == "object") {
                argumentString += "recurrence.daysInYear=" + JSON.stringify(parameters['recurrence']['daysInYear']) + "&";
            }
        }
        if (typeof parameters['reminder'] == "string") {
            argumentString += "reminder=" + parameters['reminder'] + "&";
        }
        
        window.location = "tapfortap://mraid/createCalendarEvent/" + argumentString;
    },
    
    expand: function(url) {
        
        if (mraid.getPlacementType() == 'interstitial') {
            return;
        }
        
        if (mraid.getState() == 'expanded') {
            return;
        }

        if (url == null) {
            window.location = "tapfortap://mraid/expandWithoutURL";
        } else {
            window.location = "tapfortap://mraid/expandWithURL/" + url;
        }
        
        mraid._setState('expanded');
        
    },
    
    getCurrentPosition: function() {
        if (mraid._placementType == 'interstitial') {
            return mraid.getDefaultPosition;
        }
        return {"x": mraid._currentX, "y": mraid._currentY, "width": mraid._currentWidth, "height": mraid._currentHeight};
    },
    
    
    getDefaultPosition: function() {
        return {"x": 0, "y": 0, "width": mraid._defaultWidth, "height": mraid._defaultHeight};
    },
    
    getExpandProperties: function() {
        
        var expandPropertiesToReturn = {};
        
        if (typeof mraid._expandProperties['width'] == 'undefined') {
            expandPropertiesToReturn['width'] = mraid._screensizeWidth;
        } else {
            expandPropertiesToReturn['width'] = mraid._expandProperties['width'];
        }

        if (typeof mraid._expandProperties['height'] == 'undefined') {
            expandPropertiesToReturn['height'] = mraid._screensizeHeight;
        } else {
            expandPropertiesToReturn['height'] = mraid._expandProperties['height'];
        }

        expandPropertiesToReturn['useCustomClose'] = mraid._uses_custom_close;
        expandPropertiesToReturn['isModal'] = true; // MRAID 2

        return expandPropertiesToReturn;
    },
    
    getMaxSize: function() {
        return mraid.getScreenSize();
    },
    
    getPlacementType: function() {
        return mraid._placementType;
    },
    
    getResizeProperties: function() {
        
        if (typeof mraid._resizeProperties['width'] == "undefined") {
            throw "width is not defined";
        }

        if (typeof mraid._resizeProperties['height'] == "undefined") {
            throw "height is not defined";
        }

        if (typeof mraid._resizeProperties['offsetX'] == "undefined") {
            throw "offsetX is not defined";
        }

        if (typeof mraid._resizeProperties['offsetY'] == "undefined") {
            throw "offsetY is not defined";
        }
        
        return mraid._resizeProperties;

    },
    
    getScreenSize: function() {
        return {"width": mraid._screensizeWidth, "height": mraid._screensizeHeight};
    },
    
    getState: function() {
        return mraid._state;
    },
    
    getVersion: function() {
        return "2.0"
    },
    
    isViewable: function() {
        return _isViewable;
    },
    
    open: function(url) {
        window.location = "tapfortap://mraid/open/" + url;
    },
    
    playVideo: function(url) {
        window.location = "tapfortap://mraid/playVideo/" + url;
    },
    
    removeEventListener: function(event, listener) {
        
        if (typeof mraid._eventListeners[event] != 'object') {
            throw 'unknown event type';
        }
        
        mraid._eventListeners[event] = mraid._eventListeners[event].filter(function (e1) {
            return ''+e1 != ''+listener; // corerce the functions to a string to get them comparing
        });

    },
    
    resize: function() {
        
        if (mraid._state == 'expanded') {
            mraid._sendErrorEvent('resize', 'Expanded ads cannot be resized');
        }
        
        if (typeof mraid._resizeProperties == "undefined" || typeof mraid._resizeProperties['width'] == "undefined" || typeof mraid._resizeProperties['height'] == "undefined" || typeof mraid._resizeProperties['offsetX'] == "undefined" || typeof mraid._resizeProperties['offsetY'] == "undefined") {
            mraid._sendErrorEvent('resize', 'Resize properties were not set');
            throw "required resize properties are not set";
        }
        
        window.location = "tapfortap://mraid/resize/" + JSON.stringify(mraid._resizeProperties);
        mraid._setState('resized');
        
    },
    
    setExpandProperties: function(properties) {
        
        // There are three settable properties.  Check for the existence and type correctness of each, then set
        // it to the _expandProperties object if appropriate
        
        if (typeof properties['width'] != "undefined") {
            if (typeof properties['width'] != "number") {
                throw "width is not a number";
            } else {
                mraid._expandProperties.width = properties.width;
            }
        }

        if (typeof properties['height'] != "undefined") {
            if (typeof properties['height'] != "number") {
                throw "height is not a number";
            } else {
                mraid._expandProperties.height = properties.height;
            }
        }

        if (typeof properties['useCustomClose'] != "undefined") {
            if (typeof properties['useCustomClose'] != "boolean") {
                throw "useCustomClose is not a boolean";
            } else {
                mraid.useCustomClose(properties['useCustomClose']);
            }
        }

    },
    
    setResizeProperties: function(properties) {
        
        // Verify that the properties object contains the required properties with the correct types
        if (typeof properties['width'] != "number") {
            throw "width is not a number";
        }
        if (typeof properties['height'] != "number") {
            throw "height is not a number";
        }
        if (typeof properties['offsetX'] != "number") {
            throw "offsetX is not a number";
        }
        if (typeof properties['offsetY'] != "number") {
            throw "offsetY is not a number";
        }
        if (typeof properties['customClosePosition'] != "string" && typeof properties['customClosePosition'] != "undefined") {
            throw "customClosePosition is not a string";
        }
        if (typeof properties['allowOffscreen'] != "boolean" && typeof properties['allowOffscreen'] != "undefined") {
            throw "allowOffscreen is not a boolean";
        }
        
        mraid._resizeProperties = properties;
        
    },
    
    storePicture: function(url) {
        window.location = "tapfortap://mraid/storePicture/" + url;
    },
    
    supports: function(feature) {
      
        if (feature == 'sms') {
            return mraid._supports_sms;
        }
        
        if (feature == 'tel') {
            return mraid._supports_tel;
        }
        
        if (feature == 'calendar') {
            return mraid._supports_calendar;
        }
        
        if (feature == 'storePicture') {
            return mraid._supports_store_picture;
        }
        
        if (feature == 'inlineVideo') {
            return mraid._supports_inline_video;
        }
        
        return false;
        
    },
    
    useCustomClose: function(use) {
        mraid._uses_custom_close = use;
        setTimeout('window.location = "tapfortap://mraid/useCustomClose/' + use + '"', 10);
    },
    
    _sendReadyEvent: function() {
        
        if (typeof mraid._eventListeners['ready'] != 'object') {
            throw 'error sending ready events';
        }
        
        var listenersForEvent = mraid._eventListeners['ready'];
        for (var i=0; i<listenersForEvent.length; i++) {
            listenersForEvent[i]();
        }
        
    },

    _sendErrorEvent: function(message, action) {
        
        if (typeof mraid._eventListeners['error'] != 'object') {
            throw 'error sending error events';
        }
        
        var listenersForEvent = mraid._eventListeners['error'];
        for (var i=0; i<listenersForEvent.length; i++) {
            listenersForEvent[i](message, action);
        }
        
    },

    _sendStateChangeEvent: function(state) {
        
        if (typeof mraid._eventListeners['stateChange'] != 'object') {
            throw 'error sending stateChange events';
        }
        
        var listenersForEvent = mraid._eventListeners['stateChange'];
        for (var i=0; i<listenersForEvent.length; i++) {
            listenersForEvent[i](state);
        }
        
    },

    _sendSizeChangeEvent: function(width, height) {
        
        if (typeof mraid._eventListeners['sizeChange'] != 'object') {
            throw 'error sending sizeChange events';
        }
        
        var listenersForEvent = mraid._eventListeners['sizeChange'];
        for (var i=0; i<listenersForEvent.length; i++) {
            listenersForEvent[i](width, height);
        }
        
    },

    _sendViewableChangeEvent: function(viewable) {
        
        if (typeof mraid._eventListeners['viewableChange'] != 'object') {
            throw 'error sending viewableChange events';
        }
        
        var listenersForEvent = mraid._eventListeners['viewableChange'];
        for (var i=0; i<listenersForEvent.length; i++) {
            listenersForEvent[i](viewable);
        }
        
    },
    
    _setState: function(state) {
        
        mraid._state = state;
        mraid._sendStateChangeEvent(state);
        
    }

};