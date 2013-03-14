TagLib = (function() {
	
var instance = {
		
ArrayBufferStream: (function() {
	Class = function(arrayBuffer) {
		this.buffer = new Int8Array(arrayBuffer);
		this.position = 0;
	};
	Class.prototype.readBlock = function(length, start) {
		if (start === undefined) {
			this.debug("readBlock", length);
		} else {
			this.debug("readBlock", length, start);
			this.position = start;
		}
		var block = this.buffer.subarray(this.position, this.position + length);
		this.position += block.length;
		return block;
	};

	Class.prototype.writeBlock = function(data, start) {
		if (start === undefined) {
			this.debug("writeBlock", data.length);
		} else {
			this.debug("writeBlock", data.length, start);
			this.position = start;
		}
		this.__writeBlock(data);
	};
	Class.prototype.__writeBlock = function(data) {
		if ((this.position + data.length) > this.buffer.length) {
			var prevBuffer = this.buffer;
			this.buffer = new Int8Array(this.position + data.length);
			this.buffer.set(prevBuffer);
		}
		this.buffer.set(data, this.position);
		this.position += data.length;
	};
	
	Class.prototype.insert = function(data, start, replace) {
		this.debug("insert", data.length, start, replace);
		var sizeDiff = data.length - replace;
		if (sizeDiff < 0) {
			this.__removeBlock(start + data.length, -sizeDiff);
		}
		else if(sizeDiff > 0) {
			var head = this.buffer.subarray(0, start);
			var tail = this.buffer.subarray(start + replace);
			this.buffer = new Int8Array(this.buffer.length + sizeDiff);
			this.buffer.set(head);
			this.buffer.set(tail, start + data.length);
		}
		this.position = start;
		this.__writeBlock(data);
	};

	Class.prototype.removeBlock = function(start, length) {
		this.debug("removeBlock", start, length);
		this.__removeBlock(start, length);
	};
	Class.prototype.__removeBlock = function(start, length) {
		var tailStart = start + length;
		var newBufferLength = start;
		if (tailStart < this.buffer.length) {
			var tail = this.buffer.subarray(tailStart);
			this.buffer.set(tail, start);
			newBufferLength += tail.length;
		}
		this.position = newBufferLength;
		this.__truncate(newBufferLength);
	};
	
	Class.prototype.seek = function(offset, p) {
		this.debug("seek", offset, p);
		switch(p) {
		case undefined:
		case 0:
			this.position = offset;
			break;
		case 1:
			this.position += offset;
			break;
		case 2:
			this.position = this.buffer.length - offset;
			break;
		}
	};
	
	Class.prototype.tell = function() {
		this.debug("tell", this.position);
	    return this.position;
	};
	
	Class.prototype.length = function() {
		this.debug("length", this.buffer.length);
	    return this.buffer.length;
	};
	
	Class.prototype.truncate = function(length) {
		this.debug("truncate", length);
	    this.__truncate(length);
	};
	Class.prototype.__truncate = function(length) {
	    if (length < this.buffer.length) {
	    	this.buffer = this.buffer.subarray(0, length);
	    } else if (length > this.buffer.length) {
	    	var newBuffer = new Int8Array(length);
	    	newBuffer.set(this.buffer);
	    	this.buffer = newBuffer;
	    }
	};
	
	Class.prototype.debug = function() { instance.debug.apply(this, arguments); };
	
	return Class;
})(),

File: (function() {
	Class = function(nativeFileObject, arrayBufferStream, originFilename) {
		this.__isSaving = false;
		this.__file = nativeFileObject;
		this.__stream = arrayBufferStream;
		this.name = originFilename;
	};
	
	Class.prototype.tag = function() {
		return this.__file.tag();
	};
	
	Class.prototype.save = function(callback) {
		if (this.__isSaving) {
			throw 'This file is being saved now!';
		}
		this.__isSaving = true;
		var startTime = new Date();
		var self = this;
		self.__file.save(function() {
			self.__isSaving = false;
			var blob = new Blob([self.__stream.buffer], {type: "application/octet-binary"});
			self.debug('Save time', new Date() - startTime);
			callback.call(self, blob);
		});
	};
	
	Class.prototype.debug = function() { instance.debug.apply(this, arguments); };
	
	return Class;
})(),

load: function(file, callback) {
	var startTime = new Date();
	var reader = new FileReader();
	var self = this;
	reader.onload = function(e) {
		var arrayBuffer = e.target.result;
		var arrayBufferStream = new self.ArrayBufferStream(arrayBuffer);
		self.plugin.load(arrayBufferStream, function(nativeFileObject) {
			var fileObject = new self.File(nativeFileObject, arrayBufferStream, file.name);
			self.debug('Load time', new Date() - startTime);
			callback.call(self, fileObject);
		});
	};
	reader.readAsArrayBuffer(file);
},

debug: function() { }

};

var plugin = null;
Object.defineProperty(instance, 'plugin', {
	get: function() {
		if (!document.body) {
			throw 'TagLib.plugin: window.document has not loaded yet!';
		}
		if (!plugin) {
			plugin = document.createElement('object');
			plugin.setAttribute('type', 'application/x-taglib');
			plugin.setAttribute('width', 0);
			plugin.setAttribute('height', 0);
			document.body.appendChild(plugin);
		}
		return plugin;
	}
});

Object.defineProperty(instance, 'isValid', {
	get: function() {
		if (!instance.plugin) {
			return;
		}
		return plugin.valid;
	}
});

return instance;
})();
