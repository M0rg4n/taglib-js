taglib-js
=========
TagLib + FireBreath = TagLib JS API

Build for Mac OS
---------
<pre><code>/$ git submodule update --init --recursive
/taglib/$ cmake -DCMAKE_BUILD_TYPE=Release -DENABLE_STATIC=ON -DBUILD_EXAMPLES=ON -DCMAKE_INSTALL_PREFIX=build
/$ ./firebreath/prepmac.sh . build/
</code></pre>
