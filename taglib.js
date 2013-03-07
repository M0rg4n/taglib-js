TagLib = {
		
ArrayBufferStream: (function() {
	Class = function(arrayBuffer) {
		this.buffer = new Int8Array(arrayBuffer);
		this.position = 0;
	};
	Class.prototype.readBlock = function(length) {
		console.debug("readBlock", length);
		var block = this.buffer.subarray(this.position, this.position + length);
		this.position += length;
		return block;
	};

	Class.prototype.writeBlock = function(data) {
		console.debug("writeBlock", data.length);
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
		console.debug("insert", data.length, start, replace);
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
		console.debug("removeBlock", start, length);
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
		console.debug("seek", offset, p);
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
		console.debug("tell", this.position);
	    return this.position;
	};
	
	Class.prototype.length = function() {
		console.debug("length", this.buffer.length);
	    return this.buffer.length;
	};
	
	Class.prototype.truncate = function(length) {
		console.debug("truncate", length);
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
	
	return Class;
})()
		
}
