TagLib = {
		
ArrayBufferStream: (function() {
	Class = function(arrayBuffer) {
		this.buffer = new Int8Array(arrayBuffer);
	};
	Class.prototype.readBlock = function(begin, end) {
		console.debug("readBlock", begin, end);
	    return this.buffer.subarray(begin, end);
	};
	Class.prototype.length = function() {
		console.debug("length", this.buffer.length);
	    return this.buffer.length;
	};
	return Class;
})()
		
}
