# DSC Engine Lib Documentation

## ```DSC::Debug```

### ```void DSC::Debug::log(const char* message, ...)```

Sends a **log** to the emulator. 

#### Parameters
- message

    Text to display. Allows wildcards mush like `printf` does:
    - `"%i"` : signed integer
    - `"%u"` : unsigned integer
    - `"%s"` : string
    - `"%b"` : short boolean (`"T"`/`"F"`)
    - `"%B"` : long boolean (`"True"`/`"False"`)
    - `"%x"` : lowercase hex
    - `"%X"` : uppercase hex
- variadic args

    Arguments that fit `message`'s wildcards.

### ```void DSC::Debug::warn(const char* message, ...)```

Sends a **warning** to the emulator. 

#### Parameters
- see [DSC::debug::log()](#void-dscdebuglogconst-char-message)

### ```void DSC::Debug::error(const char* message, ...)```

Sends an **error** to the emulator. Could suspend the execution.

#### Parameters
- see [DSC::debug::log()](#void-dscdebuglogconst-char-message)


## ```DSC::EventHandler```

Alias for function type `void(void* sender, void* args)`

### Parameters
- sender : The object that fires the event
- args : pretty much what you want



## ```DSC::Event```

Class to register and fire events.

### ```DSC::Event::Event()```

Constructs a new event.

### ```DSC::Event::operator+=(const DSC::EventHandler& e)```

Adds new event handler.

### ```DSC::Event::operator-=(const DSC::EventHandler& e)```

Removes an event handler

### ```DSC::Event::trigger(void* sender, void* args)```

Fires an event

#### Parameters

See [DSC::EventHandler()](#dsceventhandler)

## DSC::Scene

The game flow is broken into smaller individual parts called Scenes. Only one Scene can be executed at a time

### ```virtual void DSC::Scene::init()```

Provides an initializer for the Scene

### ```virtual void DSC::Scene::frame()```

Provides a per-frame logic for the Scene (is executed at each VBlank)

### ```Event DSC::Scene::key_down```

### ```Event DSC::Scene::key_held```

### ```Event DSC::Scene::key_up```

Key trigggered events. Event arg is the target key code. Event handlers look like this:

```C++
void on_key_down(void* sender, void* _keys) 
{
    // Get the keys state
    const int keys = (const int) _keys;
    // Do actions
    switch(keys)
    {
        //...
    }
}

void MyScene::init() override 
{
    keys_down += on_key_down(); // register event
}
```

### ```DSC::close()```

Closes the scene **and** clears up all the resources. `DSC::close()` returns an internal singleton object
that can be used to load up the next scene.

```C++
void MyScene::doOnGameOver()
{    
    if(win)
    {
        this->close()->next(new MyNextScene());
    }
    else
    {
        this->close()->next(new MyScene()); // reset scene
    }    
}
```

**Warning!**
- Due to the way `close()` is implemented, don't try to use statically declared `Scene`s.
    Only use pointer `Scene`s with their specialized api (`dsc_launch(...)`, `close()->next(...)`)


- Don't access any of the Scene's properies after `close()`-ing it!
    `close()` literally deletes the object in order to make room for the
    next Scene to load. 

    Don't do:

    ```C++
    class MyScene : public DSC::Scene
    {
    public:
        int my_property = 123;

        void next_scene() 
        {
            this->close()->next(new MyOtherScene(my_property));                        
            // After close(), my_property is no longer available
            // Therefore, the line above leads to runtime error
        }
    }
    ```

    Do it this way:

```C++
    class MyScene : public DSC::Scene
    {
    public:
        int my_property = 123;

        void next_scene() 
        {
            // save my_property to stack
            int my_backup = my_property;
            // Even though closing the Scene deletes its properties,
            // we can still retrieve our valuable variable from the
            // local scope
            this->close()->next(new MyOtherScene(my_backup));
        }
    }
```

- [To be verified] It is unsafe to `close()` during key events (?)

## ```DSC::Allocator```

An allocator instance behaves like `malloc`, but has a customizable memory segment, anti-leak measures 
and can force some data to be allocated at fixed addresses.

### ```DSC::Allocator::Allocator(int offset, int length)```

Construct an Allocator. 

#### Parameters

- **offset** The base segment start offset

- **length** The base segment length

An Allocator instance only works with addresses in range [offset, offset+length-1]

### ```void* DSC::Allocator::reserve(int size, int desired_offset = -1)```

The equivalent of `malloc(size)`. 

#### Parameters

- **size** Data length (works best in units of 32 bytes a.k.a. the size of a 4bpp tile)
- **desired_offset** If positive, the block of desired size tries to be placed at `offset + desired_offset`

#### Returns

An address in the allocator's effective range. If the allocation does not succeed, `nullptr` is returned instead.

### ````void release(void* address)````

`free(address)`. That's all. And don't be afraid to `release()` previosuly unallocated addresses. Nothing happens.

