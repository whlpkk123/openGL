//
//  YZKViewController.m
//  OpenGLESDemo
//
//  Created by ByteDance on 2024/10/22.
//

#import "YZKViewController.h"
#import "YZKGLView.h"
#import "YZKRender.h"

@interface YZKViewController ()
@property (nonatomic, strong) YZKGLView *glView;
@end

@implementation YZKViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    self.view.backgroundColor = [UIColor whiteColor];
    self.title = self.shaderTitle;
    
    YZKGLView *view = [[YZKGLView alloc] initWithFrame:CGRectMake(10, 150, self.view.bounds.size.width-20, self.view.bounds.size.height-300)];
    [self.view addSubview:view];
    self.glView = view;
    
    NSString *renderClass = [NSString stringWithFormat:@"YZK%@Render", self.shaderTitle];
    Class class = NSClassFromString(renderClass);
    if (class) {
        YZKRender *render = [[class alloc] init];
        render.size = view.bounds.size;
        [render prepareProgramWithShader];
        [render renderWithContext:view.context];
        view.render = render;
    }
}

- (void)dealloc {
    [self.glView.render stopRender];
}


@end
